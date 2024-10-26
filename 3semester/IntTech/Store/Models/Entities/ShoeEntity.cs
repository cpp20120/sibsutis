using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using Mocassini.Helpers.Utils;

namespace Mocassini.Helpers.Models;

[Table("Shoes")]
public class ShoeEntity
{
    [Key] public int Id { get; set; }

    [Required]
    [MaxLength(50)]
    [RegularExpression(
        ValidationUtils.AllowedRegex,
        ErrorMessage = ValidationUtils.AllowedRegexMessage
    )]
    public string Name { get; set; } = null!;

    /// <summary>
    ///   Price in kopecks
    /// </summary>
    [Required]
    [Range(0, int.MaxValue)]
    public int Price { get; set; }

    [Required] [MaxLength(50)] public string Barcode { get; set; } = null!;

    [Required]
    [MaxLength(500)]
    [RegularExpression(
        ValidationUtils.AllowedRegex,
        ErrorMessage = ValidationUtils.AllowedRegexMessage
    )]
    public string Description { get; set; } = null!;

    [Required] public ShoeGender Gender { get; set; } = ShoeGender.Unisex;

    [Required] public List<string> ImagesURLs { get; set; } = new();

    [Required] public int BrandId { get; set; }
    public BrandEntity? Brand { get; set; } = null!;

    public IEnumerable<ShoeSizeEntity>? ShoeSizes { get; set; } = null!;
}