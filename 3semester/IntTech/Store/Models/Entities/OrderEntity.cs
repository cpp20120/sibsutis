using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace Mocassini.Helpers.Models;

[Table("Orders")]
public class OrderEntity
{
    [Key] public int Id { get; set; }

    [Required] public AddressVO Address { get; set; } = null!;

    [Required] public int UserId { get; set; }
    public UserEntity? User { get; set; }

    [Required] public OrderStatus Status { get; set; } = OrderStatus.Pending;

    public string? Comment { get; set; }

    public string? TrackingNumber { get; set; }

    public IEnumerable<OrderItemEntity>? Items { get; set; }

    [Required] public DateTime CreatedAt { get; set; } = DateTime.Now;
}