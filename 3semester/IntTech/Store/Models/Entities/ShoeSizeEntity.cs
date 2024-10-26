using System.ComponentModel.DataAnnotations;

namespace Mocassini.Helpers.Models;

public class ShoeSizeEntity
{
    [Key] public int Id { get; set; }

    [Required]
    public int ShoeId { get; set; }
    public ShoeEntity? Shoe { get; set; } = null!;

    [Required]
    public int Size { get; set; } = 0;

    [Required]
    public int Quantity { get; set; } = 0;
    
    public IEnumerable<OrderItemEntity> OrderItems { get; set; } = null!;
}