using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Mocassini.Helpers.Models;

namespace Mocassini.Helpers.Controllers;

[ApiController]
[Route("[controller]")]
public class ShoeController : Controller
{
    private readonly ILogger<ShoeController> _logger;
    private readonly AppDbContext _dbContext;

    public ShoeController(ILogger<ShoeController> logger, AppDbContext dbContext)
    {
        _logger = logger;
        _dbContext = dbContext;
    }

    public class GetFilters
    {
        public string? Name { get; set; }
        public int? BrandId { get; set; }
        public int? MinPrice { get; set; }
        public int? MaxPrice { get; set; }
    }

    [HttpGet(Name = "GetShoes")]
    public IEnumerable<ShoeEntity> Get([FromQuery] GetFilters? filters)
    {
        filters ??= new GetFilters();

        return _dbContext.Shoes
            .Select(
                c => new ShoeEntity
                {
                    Id = c.Id,
                    Name = c.Name,
                    Description = c.Description,
                    BrandId = c.BrandId,
                    Price = c.Price,
                    Barcode = c.Barcode,
                    Gender = c.Gender,
                    ImagesURLs = c.ImagesURLs,

                    Brand = new BrandEntity
                    {
                        Id = c.Brand.Id,
                        Name = c.Brand.Name,
                        Description = c.Brand.Description,
                        ExternalLogoId = c.Brand.ExternalLogoId,
                    },

                    ShoeSizes = c.ShoeSizes.Select(
                        ss => new ShoeSizeEntity
                        {
                            Id = ss.Id,
                            ShoeId = ss.ShoeId,
                            Size = ss.Size,
                            Quantity = ss.Quantity
                        }
                    ).ToList(),
                }
            )
            .Where(
                c =>
                    (filters.Name == null || c.Name.Contains(filters.Name)) &&
                    (filters.BrandId == null || c.BrandId == filters.BrandId) &&
                    (filters.MinPrice == null || c.Price >= filters.MinPrice) &&
                    (filters.MaxPrice == null || c.Price <= filters.MaxPrice)
            )
            .ToList();
    }

    [HttpGet("{id}", Name = "GetShoe")]
    public ShoeEntity Get(int id)
    {
        return _dbContext.Shoes
            .Select(c => new ShoeEntity
                {
                    Id = c.Id,
                    Name = c.Name,
                    Description = c.Description,
                    BrandId = c.BrandId,
                    Price = c.Price,
                    Barcode = c.Barcode,
                    Gender = c.Gender,
                    ImagesURLs = c.ImagesURLs,
                    
                    Brand = new BrandEntity
                    {
                        Id = c.Brand.Id,
                        Name = c.Brand.Name,
                        Description = c.Brand.Description,
                        ExternalLogoId = c.Brand.ExternalLogoId,
                    },
                    
                    ShoeSizes = c.ShoeSizes.Select(
                        ss => new ShoeSizeEntity
                        {
                            Id = ss.Id,
                            ShoeId = ss.ShoeId,
                            Size = ss.Size,
                            Quantity = ss.Quantity
                        }
                    ).ToList(),
                }
            )
            .First(c => c.Id == id);
    }

    public class CreateShoeRequest
    {
        public string Name { get; set; } = null!;
        public string Description { get; set; } = null!;
        public string Barcode { get; set; } = null!;
        public int BrandId { get; set; }
        public int Price { get; set; }

        // size to quantity mapping
        public Dictionary<int, int> ShoeSizes { get; set; } = null!;
    }

    [HttpPost(Name = "CreateShoe")]
    public ShoeEntity Create([FromBody] CreateShoeRequest req)
    {
        var shoe = new ShoeEntity
        {
            Name = req.Name,
            Description = req.Description,
            BrandId = req.BrandId,
            Price = req.Price,
            Barcode = req.Barcode,
        };
        //ss - shoe sizes
        shoe.ShoeSizes = req.ShoeSizes.Select(
            ss => new ShoeSizeEntity
            {
                Shoe = shoe,
                Size = ss.Key,
                Quantity = ss.Value
            }
        ).ToList();

        _dbContext.Shoes.Add(shoe);
        _dbContext.SaveChanges();

        return shoe;
    }

    [HttpDelete("{id}", Name = "DeleteShoe")]
    public void Delete(int id)
    {
        var shoe = _dbContext.Shoes.Find(id);
        _dbContext.Shoes.Remove(shoe);
        _dbContext.SaveChanges();
    }
    
    [HttpGet("sizes", Name = "GetShoesBySizes")]
    public IEnumerable<ShoeSizeEntity> GetBySizes([FromQuery] int[] sizes)
    {
        return _dbContext.ShoeSizes
            .Where(ss => sizes.Contains(ss.Id))
            .Select(ss => new ShoeSizeEntity
                {
                    Id = ss.Id,
                    ShoeId = ss.ShoeId,
                    Size = ss.Size,
                    Quantity = ss.Quantity,
                    Shoe = new ShoeEntity
                    {
                        Id = ss.Shoe.Id,
                        Name = ss.Shoe.Name,
                        Description = ss.Shoe.Description,
                        BrandId = ss.Shoe.BrandId,
                        Price = ss.Shoe.Price,
                        ImagesURLs = ss.Shoe.ImagesURLs,
                        
                        Brand = new BrandEntity
                        {
                            Id = ss.Shoe.Brand.Id,
                            Name = ss.Shoe.Brand.Name,
                            Description = ss.Shoe.Brand.Description,
                            ExternalLogoId = ss.Shoe.Brand.ExternalLogoId,
                        },
                    },
                }
            )
            .Distinct()
            .ToList();
    }
}